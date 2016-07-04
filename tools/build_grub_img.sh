#!/bin/bash

SUBS_PAT="KERNEL_BASENAME"

error() { echo "$@" 1>&2; }
fail() { [ $# -eq 0 ] || error "$@"; exit 2; }

usage() {
    cat <<EOF
Usage: ${0##*/} output_file target_kernel grub_conf

    Build a grub disk image at output_file that will boot target_kernel
        using menu grub_conf.

    Will substitute '$SUBS_PAT' in grub_conf for base name of target_kernel.
EOF
}

# TODO: generate image manually instead of with mkrescue
build_grub_img() {
    output_file="$1"
    target_kernel="$2"
    grub_conf="$3"

    [ -f "$target_kernel" ] || { usage 1>&2; exit 1; }
    [ -f "$grub_conf" ] || { usage 1>&2; exit 1; }

    tmpdir="$(mktemp -d)" &&
    mkdir -p "$tmpdir/boot/grub" || fail "could not create tmp dirs"

    cp "$target_kernel" "$tmpdir/boot/" &&
    cat "$grub_conf" | sed -e "s/$SUBS_PAT/$(basename $target_kernel)/" \
        > "$tmpdir/boot/grub/grub.cfg" || error "file copy failed"

    grub-mkrescue -o "$output_file" "$tmpdir" || error "could not create img"

    rm -rf "$tmpdir"
}

build_grub_img "$@"
