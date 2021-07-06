class TfeTextView : Gtk.TextView {
    public File file { get; set; }
}

void app_activate(GLib.Application app) {
    print("You need a filename argument.\n");
}

void app_open(GLib.Application app, File[] files, string hint) {
    var build = new Gtk.Builder.from_resource("/com/github/ToshioCP/tfe3/tfe3.ui");
    var win = (Gtk.Window) build.get_object("win");
    win.set_application(app as Gtk.Application);
    var nb = (Gtk.Notebook) build.get_object("nb");

    foreach (File f in files) {
        try {
            uint8[] contents;   /* warning */
            f.load_contents (null, out contents, null);

            var scr = new Gtk.ScrolledWindow();
            var tv = new TfeTextView();
            var tb = tv.get_buffer();
            tv.set_wrap_mode(CHAR);
//            tv.set_editable(false);
            scr.set_child(tv);

            tv.file = f;
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

    if (nb.get_n_pages() > 0) {
        win.show();
    } else {
        win.destroy();
    }
}

int main(string[] args) {
    var app = new Gtk.Application("com.github.ToshioCP.tfe1", GLib.ApplicationFlags.HANDLES_OPEN);
    app.activate.connect(app_activate);
    app.open.connect(app_open);
    return app.run(args);
}
