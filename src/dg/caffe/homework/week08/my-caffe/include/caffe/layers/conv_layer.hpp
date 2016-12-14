#ifndef CAFFE_CONV_LAYER_HPP_
#define CAFFE_CONV_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

// #include "caffe/layers/base_conv_layer.hpp"

namespace caffe {

template <typename Dtype>
class ConvolutionLayer : public Layer<Dtype> {
 public:
  explicit ConvolutionLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}

  virtual inline const char* type() const { return "Convolution"; }

 protected:
  virtual void Forward(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
};

}  // namespace caffe

#endif  // CAFFE_CONV_LAYER_HPP_
