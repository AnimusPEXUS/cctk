#!/bin/python3

# This script is code generator for CCTK Property Description Files.
# It's a part of utils/Property.[ch]pp files

import sys
import os.path
import yaml
import fnmatch


def gen_class_properties_file(
        dest_dir,  # outputdir
        filename,  # file with instructions to generate props
):

    data = None

    filename_base = os.path.basename(filename)

    try:
        with open(filename, 'r') as f:
            txt = f.read()
            data = yaml.safe_load(txt)
    except Exception as e:
        print("couldn't read and parse file: {}".format(e))
        return

    if type(data) != list:
        print("expected list")
        return

    for class_info in data:

        if type(class_info) != dict:
            print("expected dict")
            return

        class_name = class_info['cls']
        prop_descrs = class_info['dsc']

        all_code = ''

        if type(prop_descrs) != list:
            print("expected list")
            return

        for i in prop_descrs:
            code = ''

            i['cctkpdf_filename'] = filename_base

            functional = i.get('prop_funcs', 's')

            code += '''

    // CCTK Property Description File
    // (Generated!: edit {cctkpdf_filename} and rerun _props_regen.py)

    bool p_{prop_name}_isDefaultable()
        {{
        return this->{prop_var_name}.isDefaultable();
        }}

    bool p_{prop_name}_isUndefinable()
        {{
        return this->{prop_var_name}.isUndefinable();
        }}

    bool p_{prop_name}_isValid(const {prop_type} &value)
        {{
        return this->{prop_var_name}.isValid(value);
        }}

'''.format_map(i)

            if 's' in functional:
                code += '''

    bool p_{prop_name}_set(const {prop_type} &value)
        {{
        retrun this->{prop_var_name}.set(value);
        }}

    {prop_type}    p_{prop_name}_get()
        {{
        return this->{prop_var_name}.get();
        }}

'''.format_map(i)

            if 'd' in functional:
                code += '''

    {prop_type}    p_{prop_name}_getDefault()
        {{
        return this->{prop_var_name}.getDefault();
        }}

    bool p_{prop_name}_isDefault()
        {{
        return this->{prop_var_name}.isDefault();
        }}

    bool p_{prop_name}_isDefault(const {prop_type} &value)
        {{
        return this->{prop_var_name}.isDefault(value);
        }}

    void p_{prop_name}_resetToDefault()
        {{
        this->{prop_var_name}.resetToDefault();
        }}

'''.format_map(i)

            if 'u' in functional:
                code += '''

    {prop_type}    p_{prop_name}_getUndefined()
        {{
        return this->{prop_var_name}.getUndefined();
        }}

    bool p_{prop_name}_isUndefined()
        {{
        return this->{prop_var_name}.isUndefined();
        }}

    void p_{prop_name}_undefine()
        {{
        this->{prop_var_name}.undefine();
        }}

'''.format_map(i)

            all_code += code

        new_filename = '_props_{classname}.hpp'.format(classname=class_name)
        new_filename_with_path = os.path.join(dest_dir, new_filename)

        with open(new_filename_with_path, 'w') as f:
            f.write(all_code)


def search_prop_and_cctkpdf_files(directory, props, cctkpdf):
    if type(props) != list:
        raise TypeError("props invalid type")
    if type(cctkpdf) != list:
        raise TypeError("cctkpdf invalid type")

    filelist = os.listdir(directory)
    for i in filelist:

        directory_i = os.path.join(directory, i)

        if os.path.isdir(directory_i):
            if i not in ['.git', 'build']:
                search_prop_and_cctkpdf_files(directory_i, props, cctkpdf)
            continue
        if os.path.isfile(directory_i) and not os.path.islink(directory_i):

            if fnmatch.fnmatch(i, '_props_*.hpp'):
                props.append(directory_i)
                continue

            if fnmatch.fnmatch(i, '*.cctkpdf'):
                cctkpdf.append(directory_i)
                continue

        continue


def determine_if_cctkpdf_newer_than_props(props, cctkpdf):
    if type(props) != list:
        raise TypeError("props invalid type")
    if type(cctkpdf) != list:
        raise TypeError("cctkpdf invalid type")

    props_max_time = find_max_mod_time(props)
    cctkpdf_max_time = find_max_mod_time(cctkpdf)

    if props_max_time is None or cctkpdf_max_time is None:
        return None

    return cctkpdf_max_time > props_max_time


def find_max_mod_time(filelist):
    if type(filelist) != list:
        raise TypeError("filelist invalid type")

    max_mod_time = None
    for i in filelist:
        s = os.stat(i)
        if max_mod_time == None or s.st_mtime > max_mod_time:
            max_mod_time = s.st_mtime
    return max_mod_time


def run_regeneration(props, cctkpdf):

    print("running regeneration..")

    if len(props) != 0:
        print("removing all found _props_*.hpp files")

        for i in props:
            print("  unlink {}".format(i))
            try:
                os.unlink(i)
            except:
                print("  error: couldn't unlink file")
    else:
        print("no old files to remove")

    if len(cctkpdf) != 0:
        print("generating..")

        for i in cctkpdf:
            print("  {}".format(i))
            cctkpdf_dir = os.path.dirname(i)
            gen_class_properties_file(cctkpdf_dir, i)
    else:
        print("no new files to generate from")


def main():
    argv = sys.argv
    argv_l = len(argv)
    if argv_l == 0:
        raise RuntimeError('invalid sys.argv')

    if argv_l != 1:
        raise RuntimeError('no acceptable parameters')

    if sys.argv[0] == '-c':
        raise RuntimeError('this script must be run as separate script')

    abs_script_dir = os.path.dirname(os.path.abspath(sys.argv[0]))

    props = []
    cctkpdfs = []

    print("searching for *.cctkpdf and _props_*.hpp files..")
    search_prop_and_cctkpdf_files(abs_script_dir, props, cctkpdfs)
    print()
    print("       *.cctkpdf: {}".format(len(cctkpdfs)))
    print("    _props_*.hpp: {}".format(len(props)))
    print()
    print("are cctkpdf files newer than _props_ files?: ", end='')

    newer = determine_if_cctkpdf_newer_than_props(props, cctkpdfs)
    print(newer)

    force_run = False
    if newer is None:
        print("there was error determining file ctimes -> forcing regeneration run")
        force_run = True
    else:
        force_run = newer
        if force_run:
            print("_prop_ files are old. regen required")
        else:
            print("_prop_ files are fresh. no regen")

    if force_run:
        print("it's decided to regenerate _props_ files..")

        run_regeneration(props, cctkpdfs)


if __name__ == '__main__':
    main()
