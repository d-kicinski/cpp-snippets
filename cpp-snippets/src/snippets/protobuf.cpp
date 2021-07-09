#include "array.pb.h"
#include <fstream>
#include <memory>
#include <utility>


class Parameter
{
public:
    using buffer_t = std::shared_ptr<std::vector<float>>;
    buffer_t _var;
    explicit Parameter(buffer_t var) : _var(std::move(var)){};
};


class ModelBase
{
private:
    using params_t = std::vector<std::reference_wrapper<Parameter>>;
    params_t _params;

protected:
    auto register_parameter(Parameter & param) -> void {
        _params.push_back(std::ref(param));
    }

    auto register_parameter(std::vector<std::reference_wrapper<Parameter>> & params) -> void {
        for (auto param : params) {
            _params.push_back(param);
        }
    }

public:
    virtual auto forward() -> void = 0;

    auto parameters() ->  params_t & {
       return _params;
    }
};

class Layer : public ModelBase {
public:
    using vector = std::vector<float>;
    Parameter var1;
    Parameter var2;
    Parameter var3;

    Layer() :
            var1(Parameter(std::make_shared<vector>(vector(100)))),
            var2(Parameter(std::make_shared<vector>(vector(1000)))),
            var3(Parameter(std::make_shared<vector>(vector(10000))))
    {
        register_parameter(var1);
        register_parameter(var2);
        register_parameter(var3);
    }
    auto forward() -> void override {
        std::cout << "Model::forward" << std::endl;
    }
};

class Model : public ModelBase
{
public:
    using vector = std::vector<float>;
    Parameter _param1;
    Layer _layer1;
    Layer _layer2;

    Model() :
              _param1(Parameter(std::make_shared<vector>(vector(10)))),
              _layer1(),
              _layer2()
    {
        register_parameter(_param1);
        register_parameter(_layer1.parameters());
        register_parameter(_layer2.parameters());
    }

    auto fill_variables() -> void {
        *_param1._var = vector(10, 10000.0f);
    }

    auto forward() -> void override
    {
        std::cout << "Model::forward" << std::endl;
    }
};


class Saver {
public:
    ModelBase & _model_base;
    proto::Model _proto_model;
    explicit Saver(ModelBase & model) : _model_base(model), _proto_model() {}

    auto save(std::string output_path) -> void {
        std::cout << "ModelBase::save" << std::endl;
        _proto_model.clear_variables();
        for (auto const& param: _model_base.parameters()) {
            auto* var = _proto_model.add_variables();
            for (auto v: *param.get()._var) {
                var->add_values(v);
            }
        }

        std::fstream output(output_path.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
        _proto_model.SerializePartialToOstream(&output);
    }

    auto load(std::string input_path) -> void {

        std::cout << "ModelBase::load" << std::endl;

        std::fstream input(input_path.c_str(), std::ios::in | std::ios::binary);
        if (!_proto_model.ParseFromIstream(&input)) {
            std::cerr << "Failed to parse serialized array." << std::endl;
        }

        auto & params = _model_base.parameters();

        if (params.size() != _proto_model.variables_size()) {
            std::cerr << "Saved doesn't have the same about of variables." << std::endl;
        }

        for (int i = 0; i < params.size(); ++ i) {
            const auto& var = _proto_model.variables(i);
            auto & buffer  = *params[i].get()._var;
            if (buffer.size() != var.values_size()) {
                std::cerr << "Model variable size is different than the loaded one. ";
                std::cerr << buffer.size() << " != " << var.values_size() << std::endl;
            }
            for (int j = 0; j < buffer.size(); ++j) {
                buffer[j] = var.values(j);
            }
        }
    }
};

auto main() -> int
{
    auto model = Model();
    auto saver = Saver(model);
    saver.save("empty_model.ts");
    model.fill_variables();
    saver.save("full_model.ts");

    auto other_model = Model();
    auto other_saver = Saver(other_model);
    other_saver.load("full_model.ts");
    other_saver.save("resave_full_model.ts");

    return 0;
}