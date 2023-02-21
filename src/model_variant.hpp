#include <variant>
#include <RTNeural/RTNeural.h>

using ModelType_GRU_8_1 = RTNeural::ModelT<float, 1, 1, RTNeural::GRULayerT<float, 1, 8>, RTNeural::DenseT<float, 8, 1>>;
using ModelType_LSTM_32_2 = RTNeural::ModelT<float, 2, 2, RTNeural::LSTMLayerT<float, 2, 32>, RTNeural::DenseT<float, 32, 2>>;
using ModelType_LSTM_16_2 = RTNeural::ModelT<float, 2, 2, RTNeural::LSTMLayerT<float, 2, 16>, RTNeural::DenseT<float, 16, 2>>;
using ModelType_LSTM_8_2 = RTNeural::ModelT<float, 2, 2, RTNeural::LSTMLayerT<float, 2, 8>, RTNeural::DenseT<float, 8, 2>>;
using ModelType_GRU_16_1 = RTNeural::ModelT<float, 1, 1, RTNeural::GRULayerT<float, 1, 16>, RTNeural::DenseT<float, 16, 1>>;
using ModelType_GRU_32_1 = RTNeural::ModelT<float, 1, 1, RTNeural::GRULayerT<float, 1, 32>, RTNeural::DenseT<float, 32, 1>>;
using ModelType_GRU_16_2 = RTNeural::ModelT<float, 2, 2, RTNeural::GRULayerT<float, 2, 16>, RTNeural::DenseT<float, 16, 2>>;
using ModelType_GRU_32_2 = RTNeural::ModelT<float, 2, 2, RTNeural::GRULayerT<float, 2, 32>, RTNeural::DenseT<float, 32, 2>>;
using ModelType_LSTM_8_1 = RTNeural::ModelT<float, 1, 1, RTNeural::LSTMLayerT<float, 1, 8>, RTNeural::DenseT<float, 8, 1>>;
using ModelType_LSTM_32_1 = RTNeural::ModelT<float, 1, 1, RTNeural::LSTMLayerT<float, 1, 32>, RTNeural::DenseT<float, 32, 1>>;
using ModelType_LSTM_16_1 = RTNeural::ModelT<float, 1, 1, RTNeural::LSTMLayerT<float, 1, 16>, RTNeural::DenseT<float, 16, 1>>;
using ModelType_GRU_8_2 = RTNeural::ModelT<float, 2, 2, RTNeural::GRULayerT<float, 2, 8>, RTNeural::DenseT<float, 8, 2>>;
using ModelVariantType = std::variant<ModelType_GRU_8_1,ModelType_LSTM_32_2,ModelType_LSTM_16_2,ModelType_LSTM_8_2,ModelType_GRU_16_1,ModelType_GRU_32_1,ModelType_GRU_16_2,ModelType_GRU_32_2,ModelType_LSTM_8_1,ModelType_LSTM_32_1,ModelType_LSTM_16_1,ModelType_GRU_8_2>;

inline bool is_model_type_ModelType_GRU_8_1 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "gru";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 8;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 1;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_LSTM_32_2 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "lstm";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 32;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 2;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_LSTM_16_2 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "lstm";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 16;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 2;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_LSTM_8_2 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "lstm";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 8;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 2;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_GRU_16_1 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "gru";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 16;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 1;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_GRU_32_1 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "gru";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 32;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 1;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_GRU_16_2 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "gru";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 16;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 2;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_GRU_32_2 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "gru";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 32;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 2;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_LSTM_8_1 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "lstm";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 8;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 1;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_LSTM_32_1 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "lstm";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 32;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 1;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_LSTM_16_1 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "lstm";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 16;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 1;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool is_model_type_ModelType_GRU_8_2 (const nlohmann::json& model_json) {
    const auto rnn_layer_type = model_json.at ("layers").at (0).at ("type").get<std::string>();
    const auto is_layer_type_correct = rnn_layer_type == "gru";
    const auto rnn_dim = model_json.at ("layers").at (0).at ("shape").back().get<int>();
    const auto is_rnn_dim_correct = rnn_dim == 8;
    const auto io_dim = model_json.at ("in_shape").back().get<int>();
    const auto is_io_dim_correct = io_dim == 2;
    return is_layer_type_correct && is_rnn_dim_correct && is_io_dim_correct;
}

inline bool custom_model_creator (const nlohmann::json& model_json, ModelVariantType& model) {
    if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    else if (is_model_type_ModelType_GRU_8_2 (model_json)) {
        model.emplace<ModelType_GRU_8_2>();
        return true;
    }
    return false;
}
