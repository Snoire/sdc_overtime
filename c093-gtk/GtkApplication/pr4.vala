void activate(GLib.Application app) {
    var window = new Gtk.ApplicationWindow(app as Gtk.Application);
    window.title = "vala_pr4";
    window.set_default_size(800, 600);
    window.show();
}

int main(string[] args) {
    var app = new Gtk.Application("com.github.ToshioCP.pr4", GLib.ApplicationFlags.FLAGS_NONE);
    app.activate.connect(activate);
    return app.run(args);
}
