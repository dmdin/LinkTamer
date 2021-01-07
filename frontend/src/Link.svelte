<script>
  import {apiUrl, selfUrl} from './shared';
  import {location} from 'svelte-spa-router'

  async function get() {
    let error = false;
    let resp = await fetch(apiUrl + 'url' + $location).catch(() => error = true);
    if (!error) {
      resp = await resp.json();
      window.location.replace(resp.url);
      return true;
    }
    return false;
  }

  let redirected = get()
</script>

<main>
{#await redirected}
{:then is}
  {#if is}
    <h1>Redirecting...</h1>
  {:else}
    <div>
      <h1>404</h1>
      <p>No such page or link</p>
      <a href={selfUrl}>Go back</a>
    </div>
  {/if}
{/await}
</main>

<style>
  main {
    width: 100%;
    height: 98%;
    display: grid;
    place-items: center;
    font-family: Raleway, sans-serif;
    color: #212738;
  }
  h1, p, a {
    margin: 7px;
    padding: 0;
  }
  p {
    font-size: 1.5em;
  }
  a {
    font-size: 1.5em;
  }
  h1 {
    font-size: 7em;
    color: #F97068;
    text-shadow: 0 0 10px rgba(252, 180, 177, 0.9);
  }
  div {
    display: flex;
    flex-direction: column;
    align-items: center;
  }

</style>