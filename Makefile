keepalive: keepalive-x86 keepalive-ppc
	lipo -create -o $@ $^

keepalive-x86: keepalive.c

keepalive-ppc: keepalive.c
	clang -arch ppc -O3 -o $@ $<

clean:
	rm -f keepalive keepalive-*
