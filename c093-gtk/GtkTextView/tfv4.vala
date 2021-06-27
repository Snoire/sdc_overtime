void app_activate(GLib.Application app) {
    print("You need a filename argument.\n");
}

void app_open(GLib.Application app, File[] files, string hint) {
    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.title = "file viewer";          /* 这和 set_title 效果一样 */
    win.set_default_size(800, 600);
    win.maximize();

    var nb = new Gtk.Notebook();
    win.set_child(nb);

    foreach (File f in files) {
        try {
            /* 这里有问题呀，c 语言接口要求 int8 类型，vala 接口需要 uint8 类型。。*/
            uint8[] contents;
            f.load_contents (null, out contents, null);

            var scr = new Gtk.ScrolledWindow();
            var tv = new Gtk.TextView();
            var tb = tv.get_buffer();
            tv.set_wrap_mode(CHAR);
            tv.set_editable(false);
            scr.set_child(tv);

            tb.set_text((string) contents);

            var filename = f.get_basename();
            if (filename == null) {
                filename = "";
            }
            var lab = new Gtk.Label(filename);

            nb.append_page(scr, lab);
            var nbp = nb.get_page(scr);
            nbp.tab_expand = true;
        } catch (Error e) {
            print ("Error: %s\n", e.message);
        }
    }

    if (nb.get_n_pages() > 0)
        win.show();
    else
        win.destroy();
}

int main(string[] args) {
    var app = new Gtk.Application("com.github.ToshioCP.tfv4", GLib.ApplicationFlags.HANDLES_OPEN);
    app.activate.connect(app_activate);
    app.open.connect(app_open);
    return app.run(args);
}
