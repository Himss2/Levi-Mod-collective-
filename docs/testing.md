
---

## 6. `docs/testing.md`

```markdown
# Testing

## Foundation acceptance checks

Versi pondasi dianggap berhasil apabila:

1. GitHub Actions berhasil membangun `liblevi_visuals.so`.
2. Library menggunakan arsitektur AArch64.
3. ELF mengekspor `PLGetModRegistration`.
4. ELF membutuhkan `libpreloader.so`.
5. Semua load segment memiliki alignment `0x4000`.
6. Workflow menghasilkan file `.levipack`.
7. LeviLauncher dapat mengimpor `.levipack`.
8. ViewModel tampil di Mod Menu.
9. Freelook tampil di Mod Menu.
10. Item Physics tampil di Mod Menu.
11. Tombol hold Freelook muncul.
12. Menekan tombol Freelook tidak menyebabkan crash.
13. Pengaturan tersimpan setelah launcher dimulai ulang.
14. Disable dan enable mod tidak menyebabkan menu terdaftar dua kali.

## Expected behavior

Pada versi `0.1.0`, belum ada perubahan visual di Minecraft karena native hook
belum dipasang.

Hal yang diuji pada tahap ini hanyalah:

- loading library;
- lifecycle;
- konfigurasi;
- Mod Menu;
- native button;
- packaging;
- kompatibilitas ELF Android.

## Device testing record

Setiap pengujian perangkat sebaiknya mencatat:

```text
Device:
Android version:
CPU ABI:
Minecraft version:
LeviLauncher version:
Levi Visuals version:
Import result:
Game launch result:
Mod Menu result:
Crash log:
Additional notes:
