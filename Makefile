TARGET = brokenmoonshmup.elf
OBJS = main.o entity.o player.o projectile.o
CDI = $(subst .elf,.cdi,$(TARGET))

KOS_CFLAGS += -I${KOS_PORTS}/include/raylib
CXXFLAGS += -flto -O2

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean: rm-elf rm-cdi
	-rm -f $(OBJS) 

rm-elf:
	-rm -f $(TARGET)

rm-cdi:
	-rm -f $(CDI)

$(CDI): $(TARGET)
	mkdcdisc -s BRK-M00N1 -n "Astoria's Shoot Em Up" -v 3 -e $(TARGET) -D assets -o $(CDI)

$(TARGET): $(OBJS)
	kos-c++ -o $(TARGET) $(CXXFLAGS) $(OBJS) -lraylib -lGL -lkosutils

linux: $(OBJS)
	g++ -o brokenmoonshmup.x86_64 $(CXXFLAGS) $(OBJS) -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11

run-old: $(TARGET)
	$(KOS_LOADER) $(TARGET)

run-lxdream: $(TARGET)
	lxdream-nitro -b -u -C /home/astoria/dev/raylib4dc/BrokenMoonShmupC++/assets/ -e $(TARGET)

run-cdi: $(CDI)
	flatpak run org.flycast.Flycast $(CDI)

run: $(TARGET)
	dc-tool-ser -b 1562500 -t /dev/ttyUSB0 -x $(TARGET)

cdi: $(CDI)

dist: $(TARGET)
	-rm -f $(OBJS)
	$(KOS_STRIP) $(TARGET)
