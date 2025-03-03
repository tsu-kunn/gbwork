CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= sprite.gb

all:	$(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ -p\/mkdir\/ | grep -v make >> compile.bat

# Compile and link single file in one pass
%.gb:	%.c
	$(CC) -o $@ $< map_tile.c map_data.c chara.c

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi

