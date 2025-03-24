
## 🎬AnimBaker:

In complex Level Sequences with multiple Control Rig tracks, you can selectively bake only the sections you care about without affecting the rest of the timeline. This enables precise export of layered animation data and clean separation of Control Rig tracks without cross-contamination.

### <ins>AimOffset Example:</ins>
![ezgif-4274b6007d5e13](https://github.com/user-attachments/assets/4b157eba-49d5-4d0c-8177-9eaea0d760d4)
Using 3 base poses(Center, Left, Right) and 2 additive poses(Up, Down), we can bake out all 9 of the combinations  necessary for an AimOffset with a click of a button, while still being able to adjust the base poses, making the entire workflow non-destructive.


### <ins>Other use cases:</ins>

- Non-Destructive Idle Breaks
- Transition animations in an "attack combo" that live in a seperate section
- Corrective layers for quick fixes

<br/>

### Future Work
- Reverse linking from asset to level sequence("Open Linked LevelSequence")
- Automatic additive base pose assignment in baked sequence for additive layers by default
- Better handling of controls when switching between sections
- DragAndDrop reordering
