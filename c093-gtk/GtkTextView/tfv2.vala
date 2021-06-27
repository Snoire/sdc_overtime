void app_activate(GLib.Application app) {
    var text =
"""Once upon a time, there was an old man who was called Taketori-no-Okina. It is a japanese word that means a man whose work is making bamboo baskets.
One day, he went into a mountain and found a shining bamboo. "What a mysterious bamboo it is!," he said. He cut it, then there was a small cute baby girl in it. The girl was shining faintly. He thought this baby girl is a gift from Heaven and took her home.
His wife was surprized at his tale. They were very happy because they had no children.""";

    var win = new Gtk.ApplicationWindow(app as Gtk.Application);
    win.title = "Taketori";
    win.set_default_size(800, 600);

    var scr = new Gtk.ScrolledWindow();
    win.set_child(scr);

    var tv = new Gtk.TextView();
    var tb = tv.get_buffer();
    tb.set_text(text);      /* 第二个参数默认是 -1 */
    tv.set_wrap_mode(CHAR);

    scr.set_child(tv);

    win.show();
}

int main(string[] args) {
    var app = new Gtk.Application("com.github.ToshioCP.tfv1", GLib.ApplicationFlags.FLAGS_NONE);
    app.activate.connect(app_activate);
    return app.run(args);
}
