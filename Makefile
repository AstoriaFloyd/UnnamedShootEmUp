TARGET = brokenmoonshmup.elf
OBJS = main.o entity.o player.o projectile.o
CDI = $(subst .elf,.cdi,$(TARGET))

KOS_CFLAGS += -I${KOS_PORTS}/include/raylib

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean: rm-elf rm-cdi
	-rm -f $(OBJS) 

rm-elf:
	-rm -f $(TARGET)

rm-cdi:
	-rm -f $(CDI)

$(CDI): $(TARGET)
	mkdcdisc -e $(TARGET) -o $(CDI)

$(TARGET): $(OBJS)
	kos-c++ -o $(TARGET) $(OBJS) -lraylib -lGL -lkosutils


run-old: $(TARGET)
	$(KOS_LOADER) $(TARGET)

run: $(TARGET)
	flatpak run org.flycast.Flycast $(TARGET)

run-cdi: $(CDI)
	flatpak run org.flycast.Flycast $(CDI)

cdi: $(CDI)

dist: $(TARGET)
	-rm -f $(OBJS)
	$(KOS_STRIP) $(TARGET)
