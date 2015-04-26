#include <gtk/gtk.h>
#include <string.h>

extern GtkWidget* find_child(GtkWidget* parent, const gchar* name);

GObject *
g_object_clone(GObject *src)
{
    GObject *dst;
    GParameter *params;
    GParamSpec **specs;
    guint n, n_specs, n_params;

    specs = g_object_class_list_properties(G_OBJECT_GET_CLASS(src), &n_specs);
    params = g_new0(GParameter, n_specs);
    n_params = 0;

    for (n = 0; n < n_specs; ++n)
        if (strcmp(specs[n]->name, "parent") &&
            (specs[n]->flags & G_PARAM_READWRITE) == G_PARAM_READWRITE) {
            params[n_params].name = g_intern_string(specs[n]->name);
            g_value_init(&params[n_params].value, specs[n]->value_type);
            g_object_get_property(src, specs[n]->name, &params[n_params].value);
            ++ n_params;
        }

    dst = g_object_newv(G_TYPE_FROM_INSTANCE(src), n_params, params);
    g_free(specs);
    g_free(params);

    return dst;
}
