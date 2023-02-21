import numpy as np
import warnings
warnings.filterwarnings("ignore")
import tensorflow as tf
from tensorflow import keras
tf.compat.v1.enable_eager_execution()
import matplotlib.pyplot as plt
import sys
sys.path.append('modules/RTNeural/python')
from model_utils import save_model

io_dims = 2
rnn_dims = 8
layer_type = keras.layers.LSTM
layer_name = 'GRU' if (layer_type == keras.layers.GRU) else 'LSTM'

# construct TensorFlow model
model = keras.Sequential()
model.add(keras.layers.InputLayer(input_shape=(None, io_dims)))
model.add(layer_type(rnn_dims, return_sequences=True, use_bias=True, kernel_initializer="glorot_uniform", recurrent_initializer="orthogonal", bias_initializer="random_normal",))
model.add(keras.layers.Dense(rnn_dims, activation='sigmoid', kernel_initializer=tf.keras.initializers.Orthogonal(), bias_initializer='random_normal'))
model.add(keras.layers.Dense(io_dims, kernel_initializer=tf.keras.initializers.Orthogonal(), bias_initializer='random_normal'))

# # construct signals
# N = 100
# x = 10 * np.sin(np.arange(N) * np.pi * 0.1)
# y = model.predict((x.reshape((1, -1, 1))))
# y = y.flatten()

# # plot signals
# plt.figure()
# plt.plot(x)
# plt.plot(y, '--')
# plt.ylim(-0.5, 0.5)
# # plt.savefig('python/gru_1d.png')
# plt.show()

save_model(model, f'models/{layer_name}_{rnn_dims}_{io_dims}.json')
