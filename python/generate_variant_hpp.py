
import os

directory = 'models'

model_variant_using_declarations = []
model_variant_types = []
model_type_checkers = []

for filename in os.listdir(directory):
    layer_type, rnn_dim, io_dim = filename.split('.')[0].split('_')
    print(f'Loading Model: {layer_type} w/ RNN dims {rnn_dim}, w/ I/O dims {io_dim}')

    if layer_type == 'GRU':
        rnn_layer_type = f'RTNeural::GRULayerT<float, {io_dim}, {rnn_dim}>'
    elif layer_type == 'LSTM':
        rnn_layer_type = f'RTNeural::LSTMLayerT<float, {io_dim}, {rnn_dim}>'
    dense_layer_type = f'RTNeural::DenseT<float, {rnn_dim}, {io_dim}>'
    model_type = f'RTNeural::ModelT<float, {io_dim}, {io_dim}, {rnn_layer_type}, {dense_layer_type}>'
    model_type_alias = f'ModelType_{layer_type}_{rnn_dim}_{io_dim}'
    model_variant_types.append(model_type_alias)

    model_variant_using_declarations.append(f'using {model_type_alias} = {model_type};\n')
    model_type_checkers.append(f'''inline bool is_model_type_{model_type_alias} (const nlohmann::json& model_json) {{
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "{layer_type.lower()}";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == {rnn_dim};
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == {io_dim};
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}}\n\n''')


with open("src/model_variant.hpp", "w") as header_file:
    header_file.write('#include <variant>\n')
    header_file.write('#include <RTNeural/RTNeural.h>\n')
    header_file.write('\n')

    header_file.writelines(model_variant_using_declarations)
    header_file.write(f'using ModelVariantType = std::variant<{",".join(model_variant_types)}>;\n')
    header_file.write('\n')

    header_file.writelines(model_type_checkers)
    
    header_file.write('inline bool custom_model_creator (const nlohmann::json& model_json, ModelVariantType& model) {\n')
    if_statement = 'if'
    for type_checker, alias in zip(model_type_checkers, model_variant_types):
        header_file.write(f'    {if_statement} (is_model_type_{model_type_alias} (model_json)) {{\n')
        header_file.write(f'        model.emplace<{model_type_alias}>();\n')
        header_file.write(f'        return true;\n')
        header_file.write('    }\n')
        if_statement = 'else if'
    header_file.write(f'    return false;\n')
    header_file.write('}\n')

