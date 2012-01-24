NAME = launch

SRCS = $(shell find . -name '*.cc')
OBJS = $(SRCS:.cc=.o)

CXXFLAGS = -I../includes
LDFLAGS  = -L../build -lp9 -lcppunit

all: test

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	./launch

libp9:
	make -C .. all

.PHONY: all clean fclean re libp9

$(NAME): libp9 $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)
