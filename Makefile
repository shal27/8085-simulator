SRCS 		= address_splitter.cpp alu.cpp ctrl.cpp ctrllogic.cpp flagreg.cpp idb.cpp main.cpp memdev.cpp pc.cpp register.cpp registerfile.cpp stateregister.cpp  mux2_1bit.cpp mux3.cpp mux_select.cpp

OBJS 		= $(SRCS:%.cpp=%.o)
DEPS		= $(SRCS:%.cpp=%.d)

SYSTEMC_HOME 	= /usr/local/systemc230

CXX		= g++
CXXFLAGS	= -Wall -ansi -g -O0 -Di386 
INCLUDES 	= -I $(SYSTEMC_HOME)/include

LD		= $(CXX)
LDFLAGS 	= $(CXXFLAGS)

LIBS		= -L$(SYSTEMC_HOME)/lib-linux64 -lsystemc -Wl,-rpath,/usr/local/systemc230/lib-linux64

PROGRAM 	= 8085

default:	$(PROGRAM)

$(PROGRAM):	$(OBJS) $(DEPS)
		$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o ./$@
		
test:		$(PROGRAM)
		./$<
		
clean:; 	rm -rf $(PROGRAM) *.o core* *.d *.vcd *.dump

# Cancel implicit rule
%.o:		%.cpp

%.o:		%.cpp %.d
		$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.d: 		%.cpp
		@ echo Making dependencies for $<
		@ g++ -MM $(INCLUDES) $< | sed 's#: # $*.d : #1' > $@

# Include dependency files .d
ifneq ("$(wildcard *.d)","")
  include $(wildcard *.d)
endif
