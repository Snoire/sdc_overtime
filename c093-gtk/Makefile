.PHONY : all
CFLAGS := -Wall -Wextra
CFLAGS += $(shell pkg-config --cflags gtk4)

LDFLAGS = $(shell pkg-config --libs gtk4)

VALAFLAGS := --pkg gtk4

export CFLAGS LDFLAGS VALAFLAGS

BUILD_DIRS = GtkApplication GtkLabel GtkTextView GtkTextEditor BuildSystem

all :
	@ for dir in ${BUILD_DIRS}; do \
		echo "---------------------------------------------------------"; \
		echo -e "\033[;36m              gtk/$$dir              \033[;0m"; \
		echo "---------------------------------------------------------"; \
		(cd $${dir}; ${MAKE}) ; \
		if test $$? -ne 0; then break; fi; \
	done

clean: 
	@ for dir in ${BUILD_DIRS}; do \
		(cd $${dir}; ${MAKE} clean) ;\
	done
