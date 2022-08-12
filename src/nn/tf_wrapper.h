
#include <stdbool.h>

struct TF_Tensor;

struct nlop_s;

struct tf_shared_graph_s;

extern const struct tf_shared_graph_s* tf_shared_graph_create(const char* path, const char* signature_key, bool session);
extern void tf_shared_graph_free(const struct tf_shared_graph_s* x);
extern const char* tf_shared_graph_get_init_path(const struct tf_shared_graph_s* x);


extern const struct nlop_s* nlop_tf_shared_create(const struct tf_shared_graph_s* graph);
extern const struct nlop_s* nlop_tf_create(int nr_outputs, int nr_inputs, const char* path, bool session);

