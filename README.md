## Circuit Crafter 

*Circuit Crafter* was developed as my bachelor's thesis and has since evolved into a personal hobby project that I continue to work on. It's cross platform a GUI schematic editor designed to simplify the creation of logic gate schematic designs and help with their conversion to Verilog. This tool can make the schematic design process easier and more enjoyable for hardware engineers. 

![Screenshot from 2024-12-01 22-28-02](https://github.com/user-attachments/assets/08e89857-672d-443c-a287-191c2ebb06ff)

## How to Use

Simply open the project in Qt Creator and build with QMake.


### TODO-s

1. Migrate to Qt6 ✅ 
2. Refactor to meet a design pattern (MVC) 
3. Fix any exiting leaks (Valgrind)
4. Add undo/redo stack (new item ✅, delete item, move, new edge, clear scene)
5. Implement mouse navigation ✅, and multiple item selection ✅
6. Add RMBC menu on SceneItem (delete, check)
7. Keep toolbar positions in settings 
8. Add tooltip for SceneItem
9. Add "save", "save as", "close" button/file menu options ✅ 
10. Implement SceneItem naming
11. Implement drawing of dynamic number of edges
12. Implement white/black background themes ✅ 

### Nice to Have Enhancements

* make self-fed inputs possible
* implement triggers (D, JK, T, SR)
* implement possibility for custom operators/modules
* optimize schematic parsing to a non-JSON format
* truth table generation for scheme
* layout generation

## Demo

![This is an alt text.](/image/sample.webp "This is a sample image.")


