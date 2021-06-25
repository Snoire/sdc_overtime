void activate(GLib.Application app) {
    var window = new Gtk.Window();
    window.set_application(app as Gtk.Application);
	window.show();
}

int main(string[] args) {
	var app = new Gtk.Application("com.github.ToshioCP.pr3", GLib.ApplicationFlags.FLAGS_NONE);
	app.activate.connect(activate);
	return app.run(args);
}
