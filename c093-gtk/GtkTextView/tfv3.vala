void app_activate(GLib.Application app) {
    print("You need a filename argument.\n");
}

void app_open(GLib.Application app, File[] files, string hint) {
    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.set_default_size(800, 600);

    var scr = new Gtk.ScrolledWindow();
    win.set_child(scr);

    var tv = new Gtk.TextView();
    var tb = tv.get_buffer();
    tv.set_wrap_mode(CHAR);
    tv.set_editable(false);
    scr.set_child(tv);

    try {
        /* 这里有问题呀，c 语言接口要求 int8 类型，vala 接口需要 uint8 类型。。*/
        uint8[] contents;

        files[0].load_contents (null, out contents, null);

        tb.set_text((string) contents);

        var filename = files[0].get_basename();
        if (filename != null) {
            win.title = filename;
        }

        win.show();
    } catch (Error e) {
        print ("Error: %s\n", e.message);
        win.destroy();
    }
}

int main(string[] args) {
    var app = new Gtk.Application("com.github.ToshioCP.tfv1", GLib.ApplicationFlags.HANDLES_OPEN);
    app.activate.connect(app_activate);
    app.open.connect(app_open);
    return app.run(args);
}
