#include <vector>

#include "caffe/layers/my_neuron2_layer.hpp"
#include "caffe/util/math_functions.hpp"

namespace caffe {

template <typename Dtype>
void MyNeuron2Layer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,const vector<Blob<Dtype>*>& top){
  
  NeuronLayer<Dtype>::LayerSetUp(bottom,top);
  power_ = this->layer_param_.my_neuron2_param().power();
  append_ = this->layer_param_.my_neuron2_param().append();

}

// Compute y = x^power
template <typename Dtype>
void MyNeuron2Layer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,const vector<Blob<Dtype>*>& top){

  Dtype* top_data = top[0]->mutable_cpu_data();
  const int count = bottom[0]->count();
  caffe_powx(count, bottom[0]->cpu_data(), Dtype(power_), top_data);
  caffe_add(count, bottom[0]->cpu_data(), bottom[0]->cpu_data(), top_data);
}

template <typename Dtype>
void MyNeuron2Layer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,const vector<bool>& propagate_down,const vector<Blob<Dtype>*>& bottom){
  const int count = top[0]->count();
  const Dtype* top_diff = top[0]->cpu_diff();
  if(propagate_down[0]){
    const Dtype* bottom_data = bottom[0]->cpu_data();
    Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
    caffe_powx(count, bottom_data, Dtype(power_ - 1), bottom_diff);
    caffe_scal(count, Dtype(power_), bottom_diff);
    caffe_mul(count, bottom_diff, top_diff, bottom_diff);
  }

}

#ifdef CPU_ONLY
 STUB_GPU(MyNeuron2Layer);
#endif

INSTANTIATE_CLASS(MyNeuron2Layer);
REGISTER_LAYER_CLASS(MyNeuron2);

}// namespace caffe
