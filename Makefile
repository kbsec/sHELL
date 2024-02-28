

all: submission

.PHONY: submission

submission:
	tar czf  dist/sHELL.tar.gz --exclude='*.tar.gz' --exclude='*.exe' --exclude='*.dll' src libs dist 

clean:
	-rm dist/*.exe
	-rm dist/*.dll 
	-rm dist/*.tar.gz 
