import idautils
import idc
import json
import os

def is_default_name(symbol_name):
    # Define the patterns for default names
    default_patterns = ["sub_", "dword_", "byte_", "word_", "qword_", "loc_", "unk_", "asc_", "stru_", "off_", "seg_"]
    return any(symbol_name.startswith(pattern) for pattern in default_patterns)

def dump_symbols_to_json():
    symbols = []
    functions = []
    for ea in idautils.Segments():
        for function_ea in idautils.Functions(ea, idc.get_segm_end(ea)):
            symbol_name = idc.get_func_name(function_ea)
            if is_default_name(symbol_name):
                continue
            functions.append(function_ea)
            symbol_size = idc.get_func_attr(function_ea, idc.FUNCATTR_END) - function_ea
            symbols.append({
                "name": symbol_name,
                "address": function_ea,
                "size": symbol_size
            })
    for data_ea, data_name in idautils.Names():
        if is_default_name(data_name):
            continue
        if data_ea not in functions:
            data_size = idc.get_item_size(data_ea)
            symbol_size = idc.get_item_size(data_ea)
            symbols.append({
                "name": data_name,
                "address": data_ea,
                "size": data_size,
            })

    # Convert the symbols to JSON
    json_data = json.dumps(symbols, indent=4)
    
    # Write the JSON data to a file in the current directory
    json_filename = os.path.join(os.path.dirname(__file__), 'symbols.json')
    with open(json_filename, 'w') as json_file:
        json_file.write(json_data)

    print(f"Dumped {len(symbols)} symbols to {json_filename}")

# Execute the function
dump_symbols_to_json()
