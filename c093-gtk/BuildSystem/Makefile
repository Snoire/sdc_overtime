.PHONY : make meson

make:
	@make -f tfe.mk

meson:
	meson build
	ninja -C build

clean: 
	@make -f tfe.mk clean
	/bin/rm -rf build
