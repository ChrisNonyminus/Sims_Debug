import idautils
import idc
import os

def export_symbols_to_csv():
    csv_filename = os.path.join(os.path.dirname(__file__), 'symbol_map.csv')
    header = ['Symbol Name', 'Symbol Address', 'Symbol Size', 'Source File', 'Will Decompile?', 'Decompiled?']
    
    with open(csv_filename, 'w') as csv_file:
        csv_file.write(','.join(header) + '\n')
        function_eas = []
        
        for symbol_ea in idautils.Segments():
            for function_ea in idautils.Functions(symbol_ea, idc.get_segm_end(symbol_ea)):
                function_name = idc.get_func_name(function_ea)
                function_eas.append(function_ea)
                function_size = idc.get_func_attr(function_ea, idc.FUNCATTR_END) - function_ea
                if function_size <= 5:
                    continue
                csv_file.write(f'"{function_name}",{function_ea},{function_size},"", "MAYBE", "NO"\n')
            

export_symbols_to_csv()
