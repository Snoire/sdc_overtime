void app_activate(GLib.Application app) {
    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.title = "vala_lb4";
    win.set_default_size(800, 600);

    var box = new Gtk.Box(VERTICAL, 5);
    box.set_homogeneous(true);
    win.set_child(box);

    var btn1 = new Gtk.Button.with_label("Hello.");
    btn1.clicked.connect((btn) => {
        var s = btn.get_label();
        if (strcmp(s, "Hello.") == 0)
            btn.set_label("Good-bye.");
        else
            btn.set_label("Hello.");
    });

    var btn2 = new Gtk.Button.with_label("Quit");
    btn2.clicked.connect((btn) => {
        win.destroy();      /* 在这里就可以直接访问到 win */
    });

    box.append(btn1);
    box.append(btn2);

    win.show();
}

int main(string[] args) {
    var app = new Gtk.Application("com.github.ToshioCP.lb4", GLib.ApplicationFlags.FLAGS_NONE);
    app.activate.connect(app_activate);
    return app.run(args);
}
