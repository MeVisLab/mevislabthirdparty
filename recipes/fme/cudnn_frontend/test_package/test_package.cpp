#include <cudnn_frontend.h>
#include <iostream>
#include <memory>
#include <vector>

int main()
{
    std::cout << "cudnn_frontend " << CUDNN_FRONTEND_MAJOR_VERSION << "."
              << CUDNN_FRONTEND_MINOR_VERSION << "." << CUDNN_FRONTEND_PATCH_VERSION << std::endl;
    if (CUDNN_FRONTEND_VERSION < 10000)
    {
        std::cerr << "unexpected CUDNN_FRONTEND_VERSION " << CUDNN_FRONTEND_VERSION << std::endl;
        return 1;
    }

    namespace fe = cudnn_frontend;
    fe::graph::Graph graph;
    graph.set_io_data_type(fe::DataType_t::HALF)
        .set_intermediate_data_type(fe::DataType_t::FLOAT)
        .set_compute_data_type(fe::DataType_t::FLOAT);

    const std::vector<int64_t> dim = {1, 8, 16, 16};
    const std::vector<int64_t> stride = {2048, 1, 128, 8};
    std::shared_ptr<fe::graph::Tensor_attributes> input = graph.tensor(
        fe::graph::Tensor_attributes().set_name("input").set_dim(dim).set_stride(stride));
    if (!input || input->get_name() != "input" || input->get_dim() != dim ||
        input->get_stride() != stride)
    {
        std::cerr << "tensor attributes were not stored" << std::endl;
        return 1;
    }

    std::shared_ptr<fe::graph::Tensor_attributes> output = graph.pointwise(
        input, fe::graph::Pointwise_attributes().set_mode(fe::PointwiseMode_t::RELU_FWD));
    if (!output)
    {
        std::cerr << "pointwise node creation failed" << std::endl;
        return 1;
    }
    output->set_output(true);
    std::cout << "built graph with input " << input->get_name() << " and " << dim.size()
              << " dimensions" << std::endl;
    return 0;
}
