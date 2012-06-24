hexdump test.jpg test.txt
hexdump -r test.txt test2.jpg
hexdump test2.jpg test2.txt
@echo test.jpg and test2.jpg should be identical
@echo test.txt and test2.txt should be identical