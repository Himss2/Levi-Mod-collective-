
---

## 4. `docs/architecture.md`

```markdown
# Architecture

`LeviVisualsMod` adalah satu-satunya object yang didaftarkan melalui
`PL_REGISTER_MOD`.

## Lifecycle

### load()

Bertanggung jawab untuk:

- membuat direktori konfigurasi;
- membuka `config.json`;
- membaca konfigurasi;
- menerapkan konfigurasi awal ke setiap modul.

### enable()

Bertanggung jawab untuk:

- mengaktifkan runtime;
- mendaftarkan ketiga modul ke Mod Menu;
- mendaftarkan tombol native Freelook;
- mengizinkan native hook menjalankan behavior.

### disable()

Bertanggung jawab untuk:

- menonaktifkan runtime;
- melepaskan tombol Freelook;
- menghapus seluruh entry Mod Menu;
- menghentikan behavior hook tanpa merusak game state.

### unload()

Bertanggung jawab untuk membersihkan state yang masih tersisa ketika library
dilepas.

## Module ownership

Tiga modul berada dalam satu native library, tetapi masing-masing memiliki
konfigurasi dan status aktif sendiri:

- `ViewModel`
- `Freelook`
- `ItemPhysics`

## Hook ownership

Native hook Minecraft akan dikelola oleh satu central hook layer.

Setiap target function hanya boleh memiliki satu detour milik Levi Visuals.
Modul yang membutuhkan target yang sama akan menggunakan hook tersebut bersama
melalui dispatcher.

Pendekatan ini mencegah:

- pemasangan hook ganda;
- recursion akibat trampoline yang salah;
- konflik antar-modul;
- urutan cleanup yang tidak konsisten;
- crash ketika mod dinonaktifkan.

## Runtime gating

Hook dapat tetap terpasang selama library aktif, tetapi behavior hook wajib
memeriksa:

1. apakah Levi Visuals sedang aktif;
2. apakah modul terkait sedang aktif;
3. apakah signature dan ABI target sudah tervalidasi;
4. apakah object Minecraft yang diterima valid.

Jika salah satu kondisi gagal, hook langsung meneruskan pemanggilan ke fungsi
original.
---

## 4. `docs/architecture.md`

```markdown
# Architecture

`LeviVisualsMod` adalah satu-satunya object yang didaftarkan melalui
`PL_REGISTER_MOD`.

## Lifecycle

### load()

Bertanggung jawab untuk:

- membuat direktori konfigurasi;
- membuka `config.json`;
- membaca konfigurasi;
- menerapkan konfigurasi awal ke setiap modul.

### enable()

Bertanggung jawab untuk:

- mengaktifkan runtime;
- mendaftarkan ketiga modul ke Mod Menu;
- mendaftarkan tombol native Freelook;
- mengizinkan native hook menjalankan behavior.

### disable()

Bertanggung jawab untuk:

- menonaktifkan runtime;
- melepaskan tombol Freelook;
- menghapus seluruh entry Mod Menu;
- menghentikan behavior hook tanpa merusak game state.

### unload()

Bertanggung jawab untuk membersihkan state yang masih tersisa ketika library
dilepas.

## Module ownership

Tiga modul berada dalam satu native library, tetapi masing-masing memiliki
konfigurasi dan status aktif sendiri:

- `ViewModel`
- `Freelook`
- `ItemPhysics`

## Hook ownership

Native hook Minecraft akan dikelola oleh satu central hook layer.

Setiap target function hanya boleh memiliki satu detour milik Levi Visuals.
Modul yang membutuhkan target yang sama akan menggunakan hook tersebut bersama
melalui dispatcher.

Pendekatan ini mencegah:

- pemasangan hook ganda;
- recursion akibat trampoline yang salah;
- konflik antar-modul;
- urutan cleanup yang tidak konsisten;
- crash ketika mod dinonaktifkan.

## Runtime gating

Hook dapat tetap terpasang selama library aktif, tetapi behavior hook wajib
memeriksa:

1. apakah Levi Visuals sedang aktif;
2. apakah modul terkait sedang aktif;
3. apakah signature dan ABI target sudah tervalidasi;
4. apakah object Minecraft yang diterima valid.

Jika salah satu kondisi gagal, hook langsung meneruskan pemanggilan ke fungsi
original.
