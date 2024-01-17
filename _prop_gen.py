
# This script is code generator for CCTK Property Description Files.
# It's a part of utils/Property.[ch]pp files

import sys
import os.path
import yaml


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
    // (Generated!: edit {cctkpdf_filename} and rerun `_prop_gen.py ./{cctkpdf_filename}`)

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


def main():
    argv = sys.argv
    argv_l = len(argv)
    if argv_l == 0:
        raise RuntimeError('invalid sys.argv')

    if argv_l != 2:
        print('invalid argument')
        return

    arg = argv[1]

    filename = os.path.abspath(arg)
    filename_dir = os.path.dirname(filename)

    if not os.path.exists(filename) or not os.path.isfile(filename):
        print("file not exists")
        return

    print(filename)
    print(filename_dir)

    if not filename.endswith('.cctkpdf'):
        print("invalid file")
        return

    gen_class_properties_file(filename_dir, filename)


if __name__ == '__main__':
    main()
