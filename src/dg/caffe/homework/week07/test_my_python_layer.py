import six
import caffe
import numpy as np
import argparse, pprint

class MyPython(caffe.Layer):
    """A layer that just multiplies by ten"""

    def setup(self, bottom, top):
        pass

    def reshape(self, bottom, top):
        top[0].reshape(*bottom[0].data.shape)

    def forward(self, bottom, top):
        top[0].data[...] = np.power(bottom[0].data, int(self.param_str))

    def backward(self, top, propagate_down, bottom):
        bottom[0].diff[...] = 10 * top[0].diff


deploy_file = "./deploy_my_python_layer.prototxt"
test_data   = "./5.jpg"


if __name__ == '__main__':
    net = caffe.Net(deploy_file, caffe.TEST)
    net = caffe.Net(deploy_file,caffe.TEST)
    transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})
    transformer.set_transpose('data', (2, 0, 1))
    img = caffe.io.load_image(test_data,color=False)
    net.blobs['data'].data[...] = transformer.preprocess('data', img)
    print net.blobs['data'].data[0][0][14]
    out = net.forward()
    print out['data_out'][0][0][14]
