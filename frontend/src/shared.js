import {writable} from "svelte/store";

export const apiUrl = writable();
export const selfUrl = writable();

if (process.env.isProd) {
    apiUrl.set("https://backend.linktamer.xyz/");
    selfUrl.set("https://linktamer.xyz/");
} else {
    apiUrl.set("http://localhost:8000/");
    selfUrl.set("http://localhost:5000/");
}
