keepalive: keepalive-x86 keepalive-x86-64 keepalive-ppc
	lipo -create -o $@ $^

keepalive-x86: keepalive.c
	clang -arch i386 -O3 -o $@ $<

keepalive-x86-64: keepalive.c
	clang -arch x86_64 -O3 -o $@ $<

keepalive-ppc: keepalive.c
	clang -arch ppc -O3 -o $@ $<

clean:
	rm -f keepalive keepalive-*
