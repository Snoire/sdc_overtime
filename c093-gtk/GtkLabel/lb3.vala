#if 0
void click_cb(Gtk.Button btn) {
    win.destroy();  /* 定义在外面就没法把 win 传进来，必须写成嵌套函数的形式吗？*/
}
#endif

void app_activate(GLib.Application app) {
    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.title = "vala_lb3";
	win.set_default_size(800, 600);

    var btn = new Gtk.Button.with_label("Quit");
    win.set_child(btn);
    btn.clicked.connect((btn) => {
        win.destroy();      /* 在这里就可以直接访问到 win */
    });

	win.show();
}

int main(string[] args) {
	var app = new Gtk.Application("com.github.ToshioCP.lb3", GLib.ApplicationFlags.FLAGS_NONE);
	app.activate.connect(app_activate);
	return app.run(args);
}
