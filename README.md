# Levi Visuals

Native LeviLauncher Android mod yang menyediakan tiga modul visual independen:

- ViewModel
- Freelook
- Item Physics

Versi `0.1.0` merupakan pondasi awal proyek. Versi ini sudah menyediakan:

- lifecycle resmi LeviLauncher;
- konfigurasi permanen;
- integrasi dengan Mod Menu;
- tombol native untuk Freelook;
- build Android ARM64;
- dukungan ELF 16 KiB;
- packaging otomatis menjadi `.levipack`.

Minecraft hook belum dipasang pada versi pondasi ini.

## Supported target

- Minecraft Bedrock `1.26.44.3`
- Android `arm64-v8a`
- LeviLauncher Android
- ELF dengan page alignment 16 KiB
- `preloader-android` `0.2.3`

## Modules

### ViewModel

Dirancang untuk mengatur transformasi dan FOV item first-person.

Target implementasi berikutnya mencakup:

- item biasa;
- block item;
- normal chest;
- trapped chest;
- ender chest;
- copper chest;
- shulker box;
- special rendered items.

### Freelook

Dirancang untuk memisahkan rotasi kamera dari rotasi tubuh pemain.

Modul akan menggunakan tombol native milik Levi Mod Menu dan tidak menggunakan
ImGui atau overlay OpenGL tambahan.

### Item Physics

Dirancang untuk mengubah orientasi dropped item tanpa membuat item terus
berputar secara horizontal.

Target implementasi mencakup:

- item biasa;
- block item;
- shield;
- banner;
- special rendered items;
- interpolasi rotasi per item entity.

## Build using GitHub Actions

1. Push seluruh source ke GitHub.
2. Buka tab `Actions`.
3. Pilih workflow `Build`.
4. Tekan `Run workflow`.
5. Setelah build selesai, buka bagian `Artifacts`.
6. Unduh file `LeviVisuals-....levipack`.

## Release

Pastikan versi pada `manifest.json` sama dengan tag release.

Contoh:

```text
v0.1.0
