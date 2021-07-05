class TfeTextView : Gtk.TextView {
    public File file { get; set; }
}

void app_activate(GLib.Application app) {
    print("You need a filename argument.\n");
}

void app_open(GLib.Application app, File[] files, string hint) {
    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.title = "file editor";
    win.set_default_size(800, 600);
    //win.maximize();

    var boxv = new Gtk.Box(VERTICAL, 0);
    win.set_child(boxv);

    var boxh = new Gtk.Box(HORIZONTAL, 0);
    boxv.append(boxh);

    var dmy1 = new Gtk.Label(null);
    dmy1.width_chars = 10;
    var dmy2 = new Gtk.Label(null);
    dmy2.set_hexpand(true);
    var dmy3 = new Gtk.Label(null);
    dmy3.width_chars = 10;

    var btnn = new Gtk.Button.with_label("New");
    var btno = new Gtk.Button.with_label("Open");
    var btns = new Gtk.Button.with_label("Save");
    var btnc = new Gtk.Button.with_label("Close");

    boxh.append(dmy1);
    boxh.append(btnn);
    boxh.append(btno);
    boxh.append(dmy2);
    boxh.append(btns);
    boxh.append(btnc);
    boxh.append(dmy3);

    var nb = new Gtk.Notebook();
    nb.set_hexpand(true);
    nb.set_vexpand(true);
    boxv.append(nb);

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
