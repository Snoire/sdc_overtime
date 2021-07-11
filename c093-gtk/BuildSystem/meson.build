project('tfe', 'vala', 'c')

# tfe
gtkdep = dependency('gtk4')

gnome=import('gnome')
resources = gnome.compile_resources('resources','tfe.gresource.xml')

csources=files('tfe.c', 'tfetextview.c')

executable('tfe', csources, resources, dependencies: gtkdep)

# vala_tfe
valadep = [
    dependency('glib-2.0'),
    dependency('gobject-2.0'),
    dependency('gtk4'),
]

valasources = files('tfe.vala', 'tfetextview.vala')

executable('vala_tfe', valasources, resources, dependencies: valadep)
