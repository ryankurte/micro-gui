
all: icons lib fonts

icons: icons_1x icons_2x icons_4x icons_6x icons_8x

fonts:
	@echo TODO

lib: 
	mkdir build; cd build; cmake .. && make; cd ..


icons_1x:
	python3 ./scripts/build-iconic.py --scale=1 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_1x.h
	python3 ./scripts/build-iconic.py --scale=1 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_1x.c

icons_2x:
	python3 ./scripts/build-iconic.py --scale=2 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_2x.h
	python3 ./scripts/build-iconic.py --scale=2 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_2x.c

icons_4x:
	python3 ./scripts/build-iconic.py --scale=4 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_4x.h
	python3 ./scripts/build-iconic.py --scale=4 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_4x.c

icons_6x:
	python3 ./scripts/build-iconic.py --scale=6 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_6x.h
	python3 ./scripts/build-iconic.py --scale=6 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_6x.c

icons_8x:
	python3 ./scripts/build-iconic.py --scale=8 --folder=./resources/open-iconic/png --template=./scripts/icon-template.h --output=./ugui/icons/icons_8x.h
	python3 ./scripts/build-iconic.py --scale=8 --folder=./resources/open-iconic/png --template=./scripts/icon-template.c --output=./source/icons/icons_8x.c

