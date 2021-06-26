void activate(GLib.Application app) {
    //stdout.printf("GtkApplication is activated.\n");
    /* 这个才是直接翻译 */
    print("GtkApplication is activated.\n");
}

int main(string[] args) {
    var app = new Gtk.Application("com.github.ToshioCP.pr2", GLib.ApplicationFlags.FLAGS_NONE);
    app.activate.connect(activate);
    return app.run(args);
}
