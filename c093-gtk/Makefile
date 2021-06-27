.PHONY : all
CFLAGS := -Wall -g
CFLAGS += $(shell pkg-config --cflags gtk4)
CFLAGS += $(shell pkg-config --libs gtk4)

VALAFLAGS := --pkg gtk4

export CFLAGS VALAFLAGS

BUILD_DIRS = GtkApplication GtkLabel GtkTextView

all :
	@ for dir in ${BUILD_DIRS}; do \
		echo "---------------------------------------------------------"; \
		echo "\033[;36m               gtk/$$dir                \033[;0m"; \
		echo "---------------------------------------------------------"; \
		(cd $${dir}; ${MAKE}) ; \
		if test $$? -ne 0; then break; fi; \
	done

clean: 
	@ for dir in ${BUILD_DIRS}; do \
		(cd $${dir}; ${MAKE} clean) ;\
	done
