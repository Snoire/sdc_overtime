void click_cb(Gtk.Button btn) {
    stdout.printf("Clicked.\n");
}

void activate(GLib.Application app) {
    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.title = "vala_lb2";
    win.set_default_size(800, 600);

    var btn = new Gtk.Button.with_label("Click me");
    win.set_child(btn);
    btn.clicked.connect(click_cb);

    win.show();
}

int main(string[] args) {
    var app = new Gtk.Application("com.github.ToshioCP.lb2", GLib.ApplicationFlags.FLAGS_NONE);
    app.activate.connect(activate);
    return app.run(args);
}
