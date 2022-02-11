PI=pi@raspberrypi.local

SUBDIRS			= examples/c-examples/u8g2_sw_i2c
TARGET			= subdirs
PHONY			+= $(TARGET) $(SUBDIRS) %.clean
OUTDIR          = bin

all: $(TARGET)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

%.clean:
	@(cd $(patsubst %.clean, %, $@) && $(MAKE) clean)

clean distclean: $(patsubst %, %.clean, $(SUBDIRS))

.PHONY: $(PHONY) install clean distclean

upload:
	scp $(OUTDIR)/* $(PI):~/
