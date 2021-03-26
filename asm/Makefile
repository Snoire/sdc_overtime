#DIRS = at\&t intel
DIRS = intel


BUILD_DIRS = ${DIRS}


all: 	
	@ for dir in ${BUILD_DIRS}; do \
		echo "---------------------------------------------------------"; \
		echo  "\033[;36m                $$dir                \033[;0m"; \
		echo "---------------------------------------------------------"; \
		(cd $${dir}; ${MAKE}) ; \
		if test $$? -ne 0; then break; fi; \
	done

echo: 
	@ for dir in ${BUILD_DIRS}; do echo $${dir}; done

clean: 
	@ for dir in ${BUILD_DIRS}; do \
		(cd $${dir}; ${MAKE} clean) ;\
		if test $$? -ne 0; then break; fi; \
	done
