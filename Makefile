keepalive: keepalive-x86 keepalive-ppc
	lipo -create -o $@ $^

keepalive-x86: keepalive.c
	gcc -isysroot /Developer/SDKs/MacOSX10.4u.sdk -mmacosx-version-min=10.4 -arch i386 -O3 -o $@ $<

keepalive-ppc: keepalive.c
	gcc -isysroot /Developer/SDKs/MacOSX10.4u.sdk -mmacosx-version-min=10.4 -arch ppc -O3 -o $@ $<

clean:
	rm -f keepalive keepalive-*
