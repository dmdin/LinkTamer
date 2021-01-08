<script>
  import {fade, draw} from 'svelte/transition';
  import {writable} from 'svelte/store';
  import CopyButton from './CopyButton.svelte';
  import {apiUrl, selfUrl} from './shared';
  // let saved = [];

  let saved = JSON.parse(localStorage.getItem('hist')) || [];
  let data = writable(saved);
  data.subscribe(_ => localStorage.setItem('hist', JSON.stringify($data)))

  let inputVal = '';
  let tamed = null;
  let hidden = true;
  if (window.location.pathname !== '/') {
    console.log(window.location.pathname);
  }

  function makeRandom(length) {
    let result = '';
    let characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    let charactersLength = characters.length;
    for (let i = 0; i < length; i++) {
      result += characters.charAt(Math.floor(Math.random() * charactersLength));
    }
    return result;
  }

  function validURL(str) {
    let pattern = new RegExp('^(https?:\\/\\/)?' + // protocol
        '((([a-z\\d]([a-z\\d-]*[a-z\\d])*)\\.)+[a-z]{2,}|' + // domain name
        '((\\d{1,3}\\.){3}\\d{1,3}))' + // OR ip (v4) address
        '(\\:\\d+)?(\\/[-a-z\\d%_.~+]*)*' + // port and path
        '(\\?[;&a-z\\d%_.~+=-]*)?' + // query string
        '(\\#[-a-z\\d_]*)?$', 'i'); // fragment locator
    return !!pattern.test(str);
  }

  async function handleClick() {
    let val = inputVal;
    if ('http' !== inputVal.slice(0, 4)) {
      val = 'http://' + val;
    }

    if (validURL(val)) {
      for (let {url, shorten} of $data){
        if (url === val){
          tamed = shorten;
          return true;
        }
      }

      let r = makeRandom(5);
      let resp = await fetch(apiUrl + 'url', {
        method: 'POST',
        body: JSON.stringify({
          "url": val,
          "shorten": r,
        }),
      }).then(res => res.json()).catch(_ => handleClick());
      tamed = selfUrl + '#/' + r;
      $data = $data.concat({url: val, shorten: tamed});
      return true;
    } else {
      hidden = false;
      setTimeout(() => hidden = true, 2000);
      return false;
    }
  }

  async function handleEnter(event) {
    if (event.key === 'Enter') {
      await handleClick();
    }
  }

</script>

<svelte:window on:keydown={handleEnter}/>
<main>
  <div class="centered-card">
    <h2 class:hidden class="error">Enter the link!</h2>
    <h1 class="title">Link<i>Tamer</i></h1>
    <p class="description">The <u>fastest</u> way to tame your URL</p>
    <input bind:value={inputVal} placeholder="https://yourlink.com">
    <button class="submit-button" on:click={handleClick}>Tame!</button>
    {#if tamed}
      <div class="new-link" transition:fade>
        <p>{tamed}</p>
        <CopyButton copyValue={tamed}/>
      </div>
    {/if}
    {#if ($data.length > 0)}
      <hr>
      <h2>Your history:</h2>
    {/if}
    <div class="history">
      {#each $data.reverse() as {url, shorten}}
        <p class="user-url">{url}</p>
        <p class="shorten-url">{shorten}</p>
        <CopyButton copyValue={shorten} size={40}/>
      {/each}
    </div>
  </div>
</main>

<style>
  .hidden {
    opacity: 0;
  }

  main {
    text-align: center;
    max-width: 1400px;
    margin: 0 auto;
    height: 99vh;
    width: 100%;
    display: grid;
    place-items: center;
    font-family: Raleway, sans-serif;
    color: #212738;
  }

  .title {
    font-weight: 800;
    font-size: 4em;
    padding: 0;
    margin: 0;
  }

  .error {
    color: crimson;
    transition: opacity 1s ease;
  }

  .description {
    font-size: 1.5em;
  }

  i {
    color: #F97068;
    text-shadow: 0 0 10px rgba(252, 180, 177, 0.9);
  }

  .centered-card {
    width: 80%;
    min-width: 300px;
    height: 600px;
  }

  input {
    border: 1px solid #cccccc;
    border-radius: 10px;
    padding: 15px;
    height: 50px;
    width: 60%;
    max-width: 400px;
    outline: none;
    transition: all 0.7s ease;
  }

  input:focus {
    border-color: #212738;
  }

  .new-link {
    display: flex;
    justify-content: center;
  }

  .submit-button {
    border-radius: 10px;
    width: 100px;
    height: 50px;
    padding: 0.7em;
    transition: all 0.7s ease;
    background: #F97068;
    border: 1px solid #F97068;
    color: #f4f4f4;
  }

  .submit-button:hover {
    background: white;
    color: #F97068;
    box-shadow: 0 0 5px 2px rgba(252, 180, 177, 0.9);
  }

  hr {
    margin: 50px auto;
    color: #212738;
    width: 50%;
    max-width: 700px;
    min-width: 400px;
  }

  .history {
    margin: 0 auto;
    display: grid;
    grid-template-columns: 1fr 1fr 30px;
    /*place-content: center;*/
    align-items: stretch;
    max-width: 800px;
  }

  .user-url {
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }

  @media (max-width: 640px) {
    input {
      width: 200px;
    }

    hr {
      width: 90%;
      min-width: 300px;
    }

    .submit-button {
      width: 70px;
    }

    .history {
      grid-template-columns: 60% 40%;
      /*place-content: center;*/
      place-items: center;
    }

    .shorten-url {
      display: none;
    }

    .user-url {
      width: 100%;
    }
  }
</style>