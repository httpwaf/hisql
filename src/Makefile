SRC=$(wildcard *.c libinjection/*.c dbms/*.c  machine-learning/*.c detect/*.c)
LIB= -lm -lrt 
OBJ=$(addprefix ./, $(addsuffix .o, $(basename $(SRC))))


___hisql_CFLAGS = -std=c99 -D_GNU_SOURCE -D_DARWIN_C_SOURCE \
                   -Wall -Wextra -Wwrite-strings -w
DEFS = -DHAVE_CONFIG_H   
INCLUDE = -I.
     
#USE_GLIB = 1

ifneq ($(USE_GLIB),)
   INCLUDE +=  -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include/ 
   LIB  += -L/usr/lib64 -lglib-2.0
   SRC  += sqlparse/*.c
   DEFS += -DHAVE_USE_GLIB
endif
   
                   
TARGET=hisql

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC)  -o $@  $^ $(CFLAGS) $(___hisql_CFLAGS) $(DEFS) $(INCLUDE) $(LDFLAGS) $(LIB)
clean:
	rm -f $(TARGET) $(OBJ)