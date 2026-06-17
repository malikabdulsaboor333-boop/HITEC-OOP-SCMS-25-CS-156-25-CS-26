# Branding Assets

## Purpose

The branding assets give the HITEC University SCMS project a consistent visual
identity for documentation, packaging, and viva presentation material.

## Final Logo

The selected logo is `logo.svg`, rendered as `logo.png` and converted into
`logo.ico`.

Visual theme:

- Shield shape for institutional identity.
- Campus building for university management.
- Graduation cap for academics.
- SCMS initials for project recognition.

## Variants

- `logo_variant_campus.svg`: building-first campus mark.
- `logo_variant_cap.svg`: academic cap mark.
- `logo_variant_minimal.svg`: simplified shield mark.

## Tooling Note

Pandoc, ImageMagick, and Inkscape were not available in the local environment.
The PNG and ICO artifacts were generated with Windows drawing APIs, while the
PDF cover page was generated with a standard-library Python fallback. The ICO
file contains multiple resolutions: 16, 32, 64, 128, and 256 px.

## Folder Icon Note

Windows `Desktop.ini` folder icons are local machine settings and are not
reliable inside ZIP submissions. For portability, the project includes
`docs/logo.ico` without changing folder attributes.
