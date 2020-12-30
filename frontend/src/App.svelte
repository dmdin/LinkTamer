
<script>
  import {writable} from 'svelte/store';
  let saved = JSON.parse(localStorage.getItem('hist'));
  let data = writable([] || saved);
  data.subscribe(_ => localStorage.setItem('hist', JSON.stringify(data)))

  let inputVal = '';

  function validURL(str) {
    var pattern = new RegExp('^(https?:\\/\\/)?'+ // protocol
        '((([a-z\\d]([a-z\\d-]*[a-z\\d])*)\\.)+[a-z]{2,}|'+ // domain name
        '((\\d{1,3}\\.){3}\\d{1,3}))'+ // OR ip (v4) address
        '(\\:\\d+)?(\\/[-a-z\\d%_.~+]*)*'+ // port and path
        '(\\?[;&a-z\\d%_.~+=-]*)?'+ // query string
        '(\\#[-a-z\\d_]*)?$','i'); // fragment locator
    return !!pattern.test(str);
  }


  async function handleClick(){
    let val = inputVal;
    if ('http' !== inputVal.slice(0, 4)){
      val = 'https://' + val;
    }
    if (validURL(val))
      $data = $data.concat(val);
  }

  async function handleEnter(event){
    if (event.key === 'Enter'){
      await handleClick();
    }
  }
</script>

<svelte:window on:keydown={handleEnter}/>
<main>
  <h1>LinkTamer</h1>
  <input bind:value={inputVal} placeholder="https://yourlink.com">
  <button on:click={handleClick}>Tame!</button>
  <div>
    {#each $data as el}
        <div>{el}</div>
    {/each}
  </div>
</main>

<style>
  main {
    text-align: center;
    padding: 1em;
    max-width: 240px;
    margin: 0 auto;
  }

  h1 {
    color: #ff3e00;
    text-transform: uppercase;
    font-size: 4em;
    font-weight: 100;
  }

  input {
    border: 1px solid #cccccc;
    border-radius: 1.5em;
    padding: 15px;
    width: 40vw;
    max-width: 400px;
    outline:none;
    transition: all 0.7s ease;
  }
  input:focus {
    border-color: #666666;
  }

  @media (max-width: 640px) {
    main {
      max-width: none;
    }
    input {
      width: 200px;
    }
  }
</style>