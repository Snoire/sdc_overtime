class TfeTextView : Gtk.TextView {
    public File file { get; set; }
}

void app_activate(GLib.Application app) {
    print("You need a filename argument.\n");
}

delegate bool CloseCallbakFunc(Gtk.Window win);

void app_open(GLib.Application app, File[] files, string hint) {
#if 0
    //https://wiki.gnome.org/Projects/Vala/SignalsAndCallbacks
    bool before_close(Gtk.Window win) { /* 好像不支持嵌套函数 */
    }
#endif

    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.title = "file editor";
    //win.set_default_size(800, 600);   /* 可省略？*/
    win.maximize();

    var nb = new Gtk.Notebook();
    win.set_child(nb);

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

    /* 但是用 delegate 和 lambda 就可以仿造嵌套函数 ^_^ */
    /* 或者直接用 lamda 。。*/
    CloseCallbakFunc before_close = (win) => {
        var n = nb.get_n_pages();
        for (var i = 0; i < n; ++i) {
            var scr = (Gtk.ScrolledWindow) nb.get_nth_page(i);
            var tv = (TfeTextView) scr.get_child();
            var file = tv.file;
            var tb = tv.get_buffer();

            Gtk.TextIter start_iter, end_iter;
            tb.get_bounds(out start_iter, out end_iter);
            var contents = tb.get_text(start_iter, end_iter, false);

            try {
                /* string.data 到底是个啥？能把 string 类型转换成 uint8[] 类型？为啥直接强制转换不行？ */
                file.replace_contents(contents.data, null, true, NONE, null);
            } catch (Error e) {
                print ("Error: %s\n", e.message);
            }
        }
        return false;
    };

    if (nb.get_n_pages() > 0) {
        win.close_request.connect(before_close);
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
