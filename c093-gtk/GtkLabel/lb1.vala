void activate(GLib.Application app) {
    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.title = "vala_lb1";
	win.set_default_size(800, 600);

    var lab = new Gtk.Label("Hello.");
    win.set_child(lab);

	win.show();
}

int main(string[] args) {
	var app = new Gtk.Application("com.github.ToshioCP.lb1", GLib.ApplicationFlags.FLAGS_NONE);
	app.activate.connect(activate);
	return app.run(args);
}
