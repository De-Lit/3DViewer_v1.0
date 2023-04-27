OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    BUILD_FILE_TMP = 3DViewerFront
    BUILD_FILE = 3DViewer
    OPEN = xdg-open
else
    BUILD_FILE_TMP = 3DViewerFront.app
    BUILD_FILE = 3DViewer.app
    OPEN = open
endif

#-------------------------------------------------------
#    Расположение каталога
#-------------------------------------------------------

TMP_DIR = ./tmp
BUILD_DIR = ../build
DIST_DIR = ./"3DViewer_v1.0"
DVI_DIR = ./"doc_3DViewer_v1"

#-------------------------------------------------------
#    Переменная для создания каталогов
#-------------------------------------------------------

BUILD = @mkdir -p $(BUILD_DIR)

TMP = @mkdir -p $(TMP_DIR)

DIST = @mkdir -p $(DIST_DIR)

#-------------------------------------------------------
#    dist name
#-------------------------------------------------------

DIST_NAME = $(DIST_DIR).tar.gz

#-------------------------------------------------------
#    Цели
#-------------------------------------------------------

all: install

install:
	$(BUILD)
	$(TMP)
	cd tmp && cmake ../3DViewerFront/. -B . && cmake --build .
	cp -R ./tmp/$(BUILD_FILE_TMP) $(BUILD_DIR)/$(BUILD_FILE)
	rm -rf tmp

uninstall:
	rm -rf $(BUILD_DIR)

dvi:
	makeinfo -o $(DVI_DIR) --html --no-warn --force ./3DViewer_v1_info.texi
	$(OPEN) $(DVI_DIR)/index.html

dist:
	$(DIST)
	cp -r Makefile ./3DViewerFront ./3DViewerBack $(DIST_DIR)
	tar -cvzf $(DIST_NAME) $(DIST_DIR)
	rm -rf $(DIST_DIR)

tests:
	cd 3DViewerBack && make test

gcov_report:
	cd 3DViewerBack && make gcov_report

make_google_style:
	cd 3DViewerBack && make make_google_style
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i **/*.h **/*.cc
	rm .clang-format

clang:
	cd 3DViewerBack && make clang
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n **/*.h **/*.cc
	rm .clang-format

cppcheck:
	cd 3DViewerBack && make cppcheck

leaks:
	cd 3DViewerBack && make leaks

clean_src:
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_NAME)
	rm -rf $(TMP_DIR)
	rm -rf $(DVI_DIR)

clean: clean_src
	rm -f s21_3dviewer.a
	cd 3DViewerBack && make clean
