SPHINX_INC := -I/usr/local/include -I/usr/local/include/sphinxbase -I/usr/local/include/pocketsphinx  
SPHINX_LIB := -L/usr/local/lib -lpocketsphinx -lsphinxbase -lsphinxad
SPHINX_MOD := \"/workspace/exam/pocketsphinx/model\"

pocketsphinx_test:
	gcc -o pocketsphinx_test pocketsphinx_test.c $(SPHINX_INC) $(SPHINX_LIB) -DMODELDIR=$(SPHINX_MOD)
clean:
	rm -f pocketsphinx_test
